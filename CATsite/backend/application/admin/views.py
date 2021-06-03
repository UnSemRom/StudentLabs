from flask import Blueprint
from flask_jwt_extended import jwt_required, get_jwt_identity
from application.base_view import BaseView
from flask_apispec import use_kwargs, marshal_with
from application import docs, session
from application.schemas import UserSchema, AuthSchema
from application.models import Admin, User

admin = Blueprint('admin', __name__)

class AdminAuthView(BaseView):
    @use_kwargs(UserSchema(only=('mail', 'password')))
    @marshal_with(AuthSchema(only=('admin_token',)))
    def post(self, **kwargs):
        try:
            admin = Admin.authenticate(**kwargs)
            token = admin.get_token()
        except Exception as e:
            #logger.warning(
            #    f'login with mail {kwargs["mail"]} failed with error: {e}')
            return {'message': str(e)}, 400
        return {'admin_token': token}


class AdminUsersView(BaseView):
    @marshal_with(UserSchema(many=True))
    def get(self):
        try:
            users = User.query.all()
            return users
            #logger.info('admin requested users list')
        except Exception as e:
            #logger.warning(
            #    f'admin failed to get users: {e}')
            return {'message': str(e)}, 400

    @use_kwargs(UserSchema)
    @marshal_with(UserSchema)
    def post(self, **kwargs):
        try:
            user = User(**kwargs)
            session.add(user)
            session.commit()
            #logger.info(
            #    f'user {user.id} created')
        except Exception as e:
            #logger.warning(
            #    f'user creation failed: {e}')
            return {'message': str(e)}, 400
        return user
