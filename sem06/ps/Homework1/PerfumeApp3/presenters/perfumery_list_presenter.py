from sqlalchemy.orm import Session
from typing import List, Dict, Any

from models.repository.perfumery_repository import PerfumeryRepository
from presenters.interfaces import PerfumeryListViewInterface


class PerfumeryListPresenter:

    def __init__(self, db: Session, view: PerfumeryListViewInterface):
        self.db = db
        self.view = view
        self.repository = PerfumeryRepository(db)

    def get_all_perfumeries(self, skip: int = 0, limit: int = 100):
        try:
            perfumeries = self.repository.get_all(skip=skip, limit=limit)
            perfumery_dicts = [self._convert_perfumery_to_dict(p) for p in perfumeries]
            return self.view.display_perfumeries(perfumery_dicts)
        except Exception as e:
            return self.view.display_error(str(e))

    def _convert_perfumery_to_dict(self, perfumery) -> Dict[str, Any]:
        return {
            'id': perfumery.id,
            'name': perfumery.name,
            'address': perfumery.address,
            'city': perfumery.city,
            'phone': perfumery.phone,
            'email': perfumery.email,
            'manager_name': perfumery.manager_name
        }