from flask import Blueprint, jsonify
from application import session, docs
from application.schemas import UserSchema, AuthSchema
from flask_apispec import use_kwargs, marshal_with
from application.models import User
from flask_jwt_extended import jwt_required

user_api = Blueprint('user_api', __name__)

@user_api.route('/login', methods=['POST'])
@use_kwargs(UserSchema(only=('mail', 'password')))
@marshal_with(AuthSchema)
def login(**kwargs):
    try:
        user = User.authenticate(**kwargs)
        token = user.get_token()
    except Exception as e:
        logger.warning(
            f'login with email {kwargs["mail"]} failed with errors: {e}')
        return {'message': str(e)}, 400
    return {'access_token': token}

@user_api.route('/register', methods=['POST'])
@use_kwargs(UserSchema)
@marshal_with(AuthSchema)
def register(**kwargs):
    try:
        user = User(**kwargs)
        session.add(user)
        session.commit()
        token = user.get_token()
    except Exception as e:
        logger.warning(
            f'registration failed with errors: {e}')
        return {'message': str(e)}, 400
    return {'access_token': token}

@user_api.route('/profile_info', methods=['GET'])
@jwt_required
def profile_info():
    user_id = get_jwt_identity()
    user_profile_info = User.get_user_info(user_id=user_id)
    return User


docs.register(register, blueprint='user_api')
docs.register(login, blueprint='user_api')