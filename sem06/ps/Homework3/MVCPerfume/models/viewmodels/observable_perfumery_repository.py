from models.db_models import Perfumery
from models.observer import Observable
from models.repositories.perfumery_repository import PerfumeryRepository


class ObservablePerfumeryRepository(PerfumeryRepository, Observable):
    def __init__(self, db):
        PerfumeryRepository.__init__(self, db)
        Observable.__init__(self)

    def create(self, name, address, city, phone=None, email=None, manager_name=None):
        result = super().create(name, address, city, phone, email, manager_name)
        self.notify_observers("create", result)
        return result

    def update(self, perfumery_id, **kwargs):
        result = super().update(perfumery_id, **kwargs)
        self.notify_observers("update", result)
        return result

    def delete(self, perfumery_id):
        result = super().delete(perfumery_id)
        self.notify_observers("delete", perfumery_id)
        return result

    def get_by_id(self, perfumery_id):
        return super().get_by_id(perfumery_id)

    def get_all(self, skip=0, limit=100):
        return super().get_all(skip, limit)

    def get_by_perfume_id(self, perfume_id):
        from models.db_models import Inventory

        inventory_items = self.db.query(Inventory).filter(Inventory.perfume_id == perfume_id).all()

        perfumery_ids = [item.perfumery_id for item in inventory_items]

        perfumeries = self.db.query(Perfumery).filter(Perfumery.id.in_(perfumery_ids)).all()

        return perfumeries
