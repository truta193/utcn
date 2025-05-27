from flask import request
from database import get_db
from presenters.inventory_management_presenter import InventoryManagementPresenter
from views.flask_views import FlaskInventoryManagementView


def new_inventory_form():
    db = next(get_db())
    view = FlaskInventoryManagementView()
    presenter = InventoryManagementPresenter(db, view)

    return presenter.show_create_form()


def create_inventory():
    db = next(get_db())
    view = FlaskInventoryManagementView()
    presenter = InventoryManagementPresenter(db, view)

    # Extract form data
    form_data = {
        'perfumery_id': request.form['perfumery_id'],
        'perfume_id': request.form['perfume_id'],
        'quantity': request.form['quantity']
    }

    return presenter.create_inventory(form_data)


def edit_inventory_form(inventory_id):
    db = next(get_db())
    view = FlaskInventoryManagementView()
    presenter = InventoryManagementPresenter(db, view)

    return presenter.show_edit_form(inventory_id)


def update_inventory(inventory_id):
    db = next(get_db())
    view = FlaskInventoryManagementView()
    presenter = InventoryManagementPresenter(db, view)

    form_data = {
        'quantity': request.form['quantity']
    }

    return presenter.update_inventory(inventory_id, form_data)


def delete_inventory(inventory_id):
    db = next(get_db())
    view = FlaskInventoryManagementView()
    presenter = InventoryManagementPresenter(db, view)

    return presenter.delete_inventory(inventory_id)