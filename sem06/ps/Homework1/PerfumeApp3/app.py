# app.py
from flask import Flask, render_template, send_from_directory
import os

from config import (
    APP_NAME,
    DEBUG_MODE,
    IMAGE_STORAGE_PATH,
    EXPORT_STORAGE_PATH
)
from database import Base, engine
from views.base_view import home, serve_image, not_found_error, internal_error

# Import view functions
from views.perfume_views import (
    list_perfumes, search_perfumes, show_perfume,
    new_perfume_form, create_perfume, edit_perfume_form,
    update_perfume, delete_perfume
)
from views.perfumery_views import (
    list_perfumeries, show_perfumery, filter_perfumery_inventory,
    new_perfumery_form, create_perfumery, edit_perfumery_form,
    update_perfumery, delete_perfumery, export_out_of_stock
)
from views.inventory_views import (
    new_inventory_form, create_inventory, edit_inventory_form,
    update_inventory, delete_inventory
)

app = Flask(__name__, template_folder='views/templates')
app.config['SECRET_KEY'] = 'your-secret-key'
app.config['UPLOAD_FOLDER'] = IMAGE_STORAGE_PATH
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # 16MB max upload

# Ensure directories exist
os.makedirs(IMAGE_STORAGE_PATH, exist_ok=True)
os.makedirs(EXPORT_STORAGE_PATH, exist_ok=True)

# Create database tables
Base.metadata.create_all(bind=engine)

# Register base routes
app.add_url_rule('/', 'home', home)
app.add_url_rule('/static/images/perfumes/<path:filename>', 'serve_image', serve_image)

# Perfume routes
app.add_url_rule('/perfumes', 'list_perfumes', list_perfumes)
app.add_url_rule('/perfumes/search', 'search_perfumes', search_perfumes)
app.add_url_rule('/perfumes/<int:perfume_id>', 'show_perfume', show_perfume)
app.add_url_rule('/perfumes/new', 'new_perfume_form', new_perfume_form)
app.add_url_rule('/perfumes/create', 'create_perfume', create_perfume, methods=['POST'])
app.add_url_rule('/perfumes/<int:perfume_id>/edit', 'edit_perfume_form', edit_perfume_form)
app.add_url_rule('/perfumes/<int:perfume_id>/update', 'update_perfume', update_perfume, methods=['POST'])
app.add_url_rule('/perfumes/<int:perfume_id>/delete', 'delete_perfume', delete_perfume, methods=['POST'])

# Perfumery routes
app.add_url_rule('/perfumeries', 'list_perfumeries', list_perfumeries)
app.add_url_rule('/perfumeries/<int:perfumery_id>', 'show_perfumery', show_perfumery)
app.add_url_rule('/perfumeries/<int:perfumery_id>/filter', 'filter_perfumery_inventory', filter_perfumery_inventory)
app.add_url_rule('/perfumeries/new', 'new_perfumery_form', new_perfumery_form)
app.add_url_rule('/perfumeries/create', 'create_perfumery', create_perfumery, methods=['POST'])
app.add_url_rule('/perfumeries/<int:perfumery_id>/edit', 'edit_perfumery_form', edit_perfumery_form)
app.add_url_rule('/perfumeries/<int:perfumery_id>/update', 'update_perfumery', update_perfumery, methods=['POST'])
app.add_url_rule('/perfumeries/<int:perfumery_id>/delete', 'delete_perfumery', delete_perfumery, methods=['POST'])
app.add_url_rule('/perfumeries/<int:perfumery_id>/export-out-of-stock/<format_type>', 'export_out_of_stock', export_out_of_stock)

# Inventory routes
app.add_url_rule('/inventory/new', 'new_inventory_form', new_inventory_form)
app.add_url_rule('/inventory/create', 'create_inventory', create_inventory, methods=['POST'])
app.add_url_rule('/inventory/<int:inventory_id>/edit', 'edit_inventory_form', edit_inventory_form)
app.add_url_rule('/inventory/<int:inventory_id>/update', 'update_inventory', update_inventory, methods=['POST'])
app.add_url_rule('/inventory/<int:inventory_id>/delete', 'delete_inventory', delete_inventory, methods=['POST'])

# Register error handlers
app.register_error_handler(404, not_found_error)
app.register_error_handler(500, internal_error)

if __name__ == '__main__':
    app.run(debug=DEBUG_MODE, host="127.0.0.1", port=63000)