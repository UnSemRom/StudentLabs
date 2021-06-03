from . import db, session, Base
from sqlalchemy.orm import relationship
from flask_jwt_extended import create_access_token
from datetime import timedelta
from passlib.hash import bcrypt

class File(Base):
    __tablename__ = 'files'
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey('User.id'))
    name = db.Column(db.String(250), nullable=False)

    @classmethod
    def get_user_list(cls, user_id):
        try:
            files = cls.query.filter(cls.user_id == user_id).all()
            session.commit()
        except Exception:
            session.rollback()
            raise
        return files

    @classmethod
    def get_list(cls):
        try:
            files = cls.query.all()
            session.commit()
        except Exception:
            session.rollback()
            raise
        return files

    def save(self):
        try:
            session.add(self)
            session.commit()
        except Exception:
            session.rollback()
            raise

    @classmethod
    def get(cls, tutorial_id, user_id):
        try:
            file = cls.query.filter(
                cls.id == tutorial_id,
                cls.user_id == user_id
            ).first()
            if not file:
                raise Exception('No tutorials with this id')
        except Exception:
            session.rollback()
            raise
        return file

    def update(self, **kwargs):
        try:
            for key, value in kwargs.items():
                setattr(self, key, value)
            session.commit()
        except Exception:
            session.rollback()
            raise

    def delete(self):
        try:
            session.delete(self)
            session.commit()
        except Exception:
            session.rollback()
            raise

class User(Base):
    __tablename__ = 'User'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(250), nullable=False)
    mail = db.Column(db.String(250), nullable=False)
    password = db.Column(db.String(100), nullable=False)
    files = relationship('File', backref = 'User', lazy = True)

    def __init__(self, **kwargs):
        self.name = kwargs.get('name')
        self.mail = kwargs.get('mail')
        self.password = bcrypt.hash(kwargs.get('password'))

    def get_token(self, expire_time=24):
        expire_delta = timedelta(expire_time)
        token = create_access_token(identity=self.id, expires_delta=expire_delta)
        return token

    @classmethod
    def authenticate(cls, mail, password):
        user = cls.query.filter(cls.mail == mail).one()
        if not bcrypt.verify(password, user.password):
            raise Exception('No user with this password')
        return user

    @classmethod
    def get_user_info(cls, user_id):
        try:
            users = cls.query.filter(cls.id == user_id).all()
            session.commit()
        except Exception:
            session.rollback()
            raise
        return users

association = db.Table('association', Base.metadata,
                       db.Column('admin_id', db.Integer,
                                 db.ForeignKey('admins.id')),
                       db.Column('role_id', db.Integer,
                                 db.ForeignKey('roles.id'))
                       )

class Admin(Base):
    __tablename__ = 'admins'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(250), nullable=False)
    mail = db.Column(db.String(250), nullable=False, unique=True)
    password = db.Column(db.String(100), nullable=False)
    roles = relationship('Role', secondary=association,
                         back_populates='admins', lazy=True)

    def __init__(self, **kwargs):
        self.name = kwargs.get('name')
        self.mail = kwargs.get('mail')
        self.password = bcrypt.hash(
            kwargs.get('password'),
            salt=Config.ADMIN_PASSWD_SALT
        )

    def get_token(self, expire_time=24):
        expire_delta = timedelta(expire_time)
        token = create_access_token(
            identity=self.id, expires_delta=expire_delta)
        return token

    @classmethod
    def authenticate(cls, mail, password):
        admin = cls.query.filter(cls.mail == mail).one()
        if not bcrypt.verify(password, admin.password):
            raise Exception('No admin with this password')
        return admin

class Role(Base):
    __tablename__ = 'roles'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(250), nullable=False)
    description = db.Column(db.String(500), nullable=False)
    admins = relationship('Admin', secondary=association,
                          back_populates='roles', lazy=True)
