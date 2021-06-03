from flask import Blueprint, jsonify, request
from application import session, docs
from application.schemas import FileSchema
from application.models import File
from flask_apispec import use_kwargs, marshal_with
from flask_jwt_extended import jwt_required, get_jwt_identity

file_api = Blueprint('file_api', __name__)

@app.route('/files/<int:file_id>', methods=['DELETE'])
@jwt_required
@marshal_with(FileSchema)
def delete_file(file_id):
    try:
        user_id = get_jwt_identity()
        item = File.get(file_id, user_id)
        item.delete()
    except Exception as e:
        logger.warning(
            f'user:{user_id} file:{file_id} - delete action failed with errors: {e}')
        return {'message': str(e)}, 400
    return '', 204

@app.route('/get_all_user_files', methods=['GET'])
@jwt_required
@marshal_with(FileSchema(many=True))
def get_all_user_files():
    try:
        user_id = get_jwt_identity()
        files = File.get_user_list(user_id=user_id)
    except Exception as e:
        logger.warning(
            f'user:{user_id} files - read action failed with errors: {e}')
        return {'message': str(e)}, 400
    return files