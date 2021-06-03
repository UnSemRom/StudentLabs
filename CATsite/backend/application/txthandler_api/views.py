from flask import Blueprint, jsonify
from application import session, docs
from flask_apispec import use_kwargs, marshal_with
from application.txt_handler import TextHandlerFrequency, TextHandlerCloud, TextHandlerSemantic
from flask import request
from werkzeug.utils import secure_filename
import os
import json
import matplotlib.pyplot as plt
import base64
import os.path

txthandler_api = Blueprint('txthandler_api', __name__)

def file_opener(files):

    textes = []

    for file in files:
        text_from_file = file.read().decode()
        textes.append(text_from_file)

    return textes

@txthandler_api.route('/comparison_frequency_analysis', methods=['POST', 'GET'])
def comparison_frequency_analysis():
    txthandler = TextHandlerFrequency()

    try:
        files = request.files.getlist('files[]')
        textes = file_opener(files)
    except Exception as e:
        logger.warning(
            f'unpacking files from request failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result = txthandler.comparison_frequency_analysis_str(textes)
    except Exception as e:
        logger.warning(
            f'comparison frequency analysis failed with errors: {e}')
        return {'message': str(e)}, 400

    return result

@txthandler_api.route('/frequency_analysis', methods=['POST', 'GET'])
def frequency_analysis():
    txthandler = TextHandlerFrequency()

    try:
        files = request.files.getlist('files[]')
        textes = file_opener(files)
    except Exception as e:
        logger.warning(
            f'unpacking files from request failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result = txthandler.frequency_analysis(textes)
    except Exception as e:
        logger.warning(
            f'frequency analysis failed with errors: {e}')
        return {'message': str(e)}, 400

    return result

@txthandler_api.route('/semantic_analysis', methods=['POST', 'GET'])
def semantic_analysis():
    txthandler = TextHandlerSemantic()

    try:
        files = request.files.getlist('files[]')
        textes = file_opener(files)
    except Exception as e:
        logger.warning(
            f'unpacking files from request failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result = txthandler.semantic_analysis(textes)
    except Exception as e:
        logger.warning(
            f'semantic analysis failed with errors: {e}')
        return {'message': str(e)}, 400

    return json.dumps(result, sort_keys=False, indent=4, ensure_ascii=False, separators=(',', ': '))

@txthandler_api.route('/get_tf_idf_query_similarity', methods=['POST', 'GET'])
def get_tf_idf_query_similarity():
    txthandler = TextHandlerSemantic()

    try:
        files = request.files.getlist('files[]')
        textes = file_opener(files)
    except Exception as e:
        logger.warning(
            f'unpacking files from request failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result = txthandler.get_tf_idf_query_similarity(textes)
    except Exception as e:
        logger.warning(
            f'get tf-idf query-similarity analysis failed with errors: {e}')
        return {'message': str(e)}, 400

    # js_result = result.to_json(force_ascii=False)
    return result

@txthandler_api.route('/WordCloud', methods=['POST', 'GET'])
def WordCloud():
    txthandler = TextHandlerCloud()

    try:
        files = request.files.getlist('files[]')
        textes = file_opener(files)
    except Exception as e:
        logger.warning(
            f'unpacking files from request failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result = txthandler.WordCloud(textes)
    except Exception as e:
        logger.warning(
            f'WordCloud(textes) function failed with errors: {e}')
        return {'message': str(e)}, 400

    try:
        result_base64image = {}

        for i in range(len(files) + 1):
            plt.imshow(result[i], interpolation='bilinear')
            plt.axis("off")

            plt.savefig('saved_figure.png')
            image = open('saved_figure.png', 'rb')
            image_read = image.read()
            base64image_b = base64.b64encode(image_read)
            base64image = base64image_b.decode('utf-8')
            result_base64image["Text" + str(i)] = base64image
            image.close()
            plt.close()

            os.remove("../backend/saved_figure.png")
    except Exception as e:
        logger.warning(
            f'something failed in result_base64image functino with errors: {e}')
        return {'message': str(e)}, 400

    return result_base64image