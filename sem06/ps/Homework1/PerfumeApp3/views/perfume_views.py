from flask import request
from database import get_db
from presenters.perfume_list_presenter import PerfumeListPresenter
from presenters.perfume_detail_presenter import PerfumeDetailPresenter
from views.flask_views import FlaskPerfumeListView, FlaskPerfumeDetailView


def list_perfumes():
    sort_desc = request.args.get('sort_desc', 'false').lower() == 'true'
    skip = int(request.args.get('skip', 0))
    limit = int(request.args.get('limit', 100))

    db = next(get_db())
    view = FlaskPerfumeListView()
    presenter = PerfumeListPresenter(db, view)

    return presenter.get_all_perfumes(skip=skip, limit=limit, sort_desc=sort_desc)


def search_perfumes():
    query = request.args.get('query', '')

    db = next(get_db())
    view = FlaskPerfumeListView()
    presenter = PerfumeListPresenter(db, view)

    return presenter.search_perfumes(query)


def show_perfume(perfume_id):
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    return presenter.show_perfume(perfume_id)


def new_perfume_form():
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    return presenter.show_create_form()


def create_perfume():
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    form_data = {
        'name': request.form['name'],
        'brand': request.form['brand'],
        'price': request.form['price'],
        'description': request.form.get('description'),
        'volume_ml': request.form.get('volume_ml'),
        'concentration': request.form.get('concentration'),
        'gender': request.form.get('gender')
    }

    image = None
    if 'image' in request.files and request.files['image'].filename:
        image = request.files['image']

    return presenter.create_perfume(form_data, image)


def edit_perfume_form(perfume_id):
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    return presenter.show_edit_form(perfume_id)


def update_perfume(perfume_id):
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    form_data = {
        'name': request.form.get('name'),
        'brand': request.form.get('brand'),
        'price': request.form.get('price'),
        'description': request.form.get('description'),
        'volume_ml': request.form.get('volume_ml'),
        'concentration': request.form.get('concentration'),
        'gender': request.form.get('gender')
    }

    image = None
    if 'image' in request.files and request.files['image'].filename:
        image = request.files['image']

    return presenter.update_perfume(perfume_id, form_data, image)


def delete_perfume(perfume_id):
    db = next(get_db())
    view = FlaskPerfumeDetailView()
    presenter = PerfumeDetailPresenter(db, view)

    return presenter.delete_perfume(perfume_id)