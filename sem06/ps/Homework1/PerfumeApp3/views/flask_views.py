# flask_views.py
from flask import render_template, flash, redirect, url_for, send_file
from typing import List, Dict, Any

from presenters.interfaces import PerfumeListViewInterface, PerfumeDetailViewInterface, PerfumeryListViewInterface, \
    PerfumeryDetailViewInterface, InventoryManagementViewInterface


class FlaskPerfumeListView(PerfumeListViewInterface):

    def display_perfumes(self, perfumes: List[Dict[str, Any]]) -> None:
        return render_template('perfumes/list.html', perfumes=perfumes)

    def display_search_results(self, perfumes: List[Dict[str, Any]], query: str) -> None:
        return render_template('perfumes/list.html',
                               perfumes=perfumes,
                               search_query=query)

    def display_error(self, message: str) -> None:
        flash(message, 'error')


class FlaskPerfumeDetailView(PerfumeDetailViewInterface):

    def display_perfume(self, perfume: Dict[str, Any], availability: List[Dict[str, Any]]) -> None:
        return render_template('perfumes/detail.html',
                               perfume=perfume,
                               availability=availability)

    def show_create_form(self) -> None:
        return render_template('perfumes/new.html')

    def show_edit_form(self, perfume: Dict[str, Any]) -> None:
        return render_template('perfumes/edit.html', perfume=perfume)

    def display_success(self, message: str) -> None:
        flash(message, 'success')

    def display_error(self, message: str) -> None:
        flash(message, 'error')

    def redirect_to_list(self) -> None:
        return redirect(url_for('list_perfumes'))

    def redirect_to_detail(self, perfume_id: int) -> None:
        return redirect(url_for('show_perfume', perfume_id=perfume_id))


class FlaskPerfumeryListView(PerfumeryListViewInterface):

    def display_perfumeries(self, perfumeries: List[Dict[str, Any]]) -> None:
        return render_template('perfumeries/list.html', perfumeries=perfumeries)

    def display_error(self, message: str) -> None:
        flash(message, 'error')


class FlaskPerfumeryDetailView(PerfumeryDetailViewInterface):

    def display_perfumery(self, perfumery: Dict[str, Any], inventory: List[Dict[str, Any]]) -> None:
        return render_template('perfumeries/detail.html',
                               perfumery=perfumery,
                               inventory=inventory)

    def display_filtered_inventory(self, perfumery: Dict[str, Any],
                                   inventory: List[Dict[str, Any]],
                                   filter_description: str) -> None:
        return render_template('perfumeries/detail.html',
                               perfumery=perfumery,
                               inventory=inventory,
                               filter_description=filter_description)

    def show_create_form(self) -> None:
        return render_template('perfumeries/new.html')

    def show_edit_form(self, perfumery: Dict[str, Any]) -> None:
        return render_template('perfumeries/edit.html', perfumery=perfumery)

    def display_success(self, message: str) -> None:
        flash(message, 'success')

    def display_error(self, message: str) -> None:
        flash(message, 'error')

    def redirect_to_list(self) -> None:
        return redirect(url_for('list_perfumeries'))

    def redirect_to_detail(self, perfumery_id: int) -> None:
        return redirect(url_for('show_perfumery', perfumery_id=perfumery_id))

    def send_export_file(self, file_path: str) -> None:
        return send_file(file_path, as_attachment=True)


class FlaskInventoryManagementView(InventoryManagementViewInterface):

    def show_create_form(self, perfumes: List[Dict[str, Any]], perfumeries: List[Dict[str, Any]]) -> None:
        return render_template('inventory/new.html',
                               perfumes=perfumes,
                               perfumeries=perfumeries)

    def show_edit_form(self, inventory: Dict[str, Any]) -> None:
        return render_template('inventory/edit.html', inventory=inventory)

    def display_success(self, message: str) -> None:
        flash(message, 'success')

    def display_error(self, message: str) -> None:
        flash(message, 'error')

    def redirect_to_perfumery(self, perfumery_id: int) -> None:
        return redirect(url_for('show_perfumery', perfumery_id=perfumery_id))