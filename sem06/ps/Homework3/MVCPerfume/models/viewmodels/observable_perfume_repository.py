from models.observer import Observable
from models.repositories.perfume_repository import PerfumeRepository


class ObservablePerfumeRepository(PerfumeRepository, Observable):
    def __init__(self, db):
        PerfumeRepository.__init__(self, db)
        Observable.__init__(self)

    def create(self, name, brand, price, description=None, volume_ml=None,
               concentration=None, gender=None, image_path=None):
        result = super().create(name, brand, price, description, volume_ml,
                                concentration, gender, image_path)
        self.notify_observers("create", result)
        return result

    def update(self, perfume_id, **kwargs):
        result = super().update(perfume_id, **kwargs)
        self.notify_observers("update", result)
        return result

    def delete(self, perfume_id):
        result = super().delete(perfume_id)
        self.notify_observers("delete", perfume_id)
        return result

    def get_all(self, skip=0, limit=100, sort_by="name", sort_desc=False):
        return super().get_all(skip, limit, sort_by, sort_desc)

    def get_by_id(self, perfume_id):
        return super().get_by_id(perfume_id)

    def filter_by_brand(self, brand, skip=0, limit=100):
        return super().filter_by_brand(brand, skip, limit)

    def search_by_name(self, name, skip=0, limit=100):
        return super().search_by_name(name, skip, limit)

    def get_all_brands(self):
        perfumes = super().get_all()
        brands = sorted(set(p.brand for p in perfumes))
        return brands
