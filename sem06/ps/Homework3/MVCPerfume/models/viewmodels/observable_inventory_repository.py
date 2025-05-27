from models.db_models import Inventory
from models.observer import Observable
from models.repositories.inventory_repository import InventoryRepository


class ObservableInventoryRepository(InventoryRepository, Observable):
    def __init__(self, db):
        InventoryRepository.__init__(self, db)
        Observable.__init__(self)

    def create(self, perfumery_id, perfume_id, quantity=0, is_available=True):
        result = super().create(perfumery_id, perfume_id, quantity, is_available)
        self.notify_observers("create", result)
        return result

    def update(self, inventory_id, **kwargs):
        result = super().update(inventory_id, **kwargs)
        self.notify_observers("update", result)
        return result

    def delete(self, inventory_id):
        result = super().delete(inventory_id)
        self.notify_observers("delete", inventory_id)
        return result

    def get_by_id(self, inventory_id):
        return super().get_by_id(inventory_id)

    def get_by_perfumery_and_perfume(self, perfumery_id, perfume_id):
        return super().get_by_perfumery_and_perfume(perfumery_id, perfume_id)

    def get_all_by_perfumery(self, perfumery_id, skip=0, limit=100):
        return super().get_all_by_perfumery(perfumery_id, skip, limit)

    def get_all_by_perfume(self, perfume_id, skip=0, limit=100):
        return super().get_all_by_perfume(perfume_id, skip, limit)

    def get_out_of_stock_by_perfumery(self, perfumery_id):
        return super().get_out_of_stock_by_perfumery(perfumery_id)

    def get_by_availability(self, perfumery_id, is_available):
        return super().get_by_availability(perfumery_id, is_available)

    def get_all(self, skip=0, limit=100):

        try:

            return super().get_all(skip, limit)
        except AttributeError:

            return self.db.query(Inventory).offset(skip).limit(limit).all()
