from . import client
from models import File

def test_simple():
    mylist = [1, 2, 3, 4, 5]

    assert 1 in mylist

def test_get():
    res = client.get('/get_all_user_files')

    assert res.status_code == 200

    assert len(res.get_json()) == len(Video.query.all())
    assert res.get_json()[0]['id'] == 1

def test_delete():
    res = client.delete('/files/1')

    assert res.status_code == 204
    assert Video.query.get(1) is None
