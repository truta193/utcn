from flask import request
from database import get_db
from presenters.perfumery_list_presenter import PerfumeryListPresenter
from presenters.perfumery_detail_presenter import PerfumeryDetailPresenter
from views.flask_views import FlaskPerfumeryListView, FlaskPerfumeryDetailView


def list_perfumeries():
    db = next(get_db())
    view = FlaskPerfumeryListView()
    presenter = PerfumeryListPresenter(db, view)

    return presenter.get_all_perfumeries()


def show_perfumery(perfumery_id):
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.show_perfumery(perfumery_id)


def filter_perfumery_inventory(perfumery_id):
    filter_type = request.args.get('filter_type')
    filter_value = request.args.get('filter_value')

    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.filter_perfumery_inventory(perfumery_id, filter_type, filter_value)


def new_perfumery_form():
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.show_create_form()


def create_perfumery():
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    form_data = {
        'name': request.form['name'],
        'address': request.form['address'],
        'city': request.form['city'],
        'phone': request.form.get('phone'),
        'email': request.form.get('email'),
        'manager_name': request.form.get('manager_name')
    }

    return presenter.create_perfumery(form_data)


def edit_perfumery_form(perfumery_id):
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.show_edit_form(perfumery_id)


def update_perfumery(perfumery_id):
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    form_data = {
        'name': request.form.get('name'),
        'address': request.form.get('address'),
        'city': request.form.get('city'),
        'phone': request.form.get('phone'),
        'email': request.form.get('email'),
        'manager_name': request.form.get('manager_name')
    }

    return presenter.update_perfumery(perfumery_id, form_data)


def delete_perfumery(perfumery_id):
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.delete_perfumery(perfumery_id)


def export_out_of_stock(perfumery_id, format_type):
    db = next(get_db())
    view = FlaskPerfumeryDetailView()
    presenter = PerfumeryDetailPresenter(db, view)

    return presenter.export_out_of_stock(perfumery_id, format_type)