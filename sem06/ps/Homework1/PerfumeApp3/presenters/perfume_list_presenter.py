import os
from sqlalchemy.orm import Session
from typing import List, Dict, Any

from models.repository.perfume_repository import PerfumeRepository
from presenters.interfaces import PerfumeListViewInterface

class PerfumeListPresenter:

    def __init__(self, db: Session, view: PerfumeListViewInterface):
        self.db = db
        self.view = view
        self.repository = PerfumeRepository(db)

    def get_all_perfumes(self, skip: int = 0, limit: int = 100, sort_desc: bool = False):
        try:
            perfumes = self.repository.get_all(skip=skip, limit=limit, sort_by="name", sort_desc=sort_desc)
            perfume_dicts = [self._convert_perfume_to_dict(p) for p in perfumes]
            return self.view.display_perfumes(perfume_dicts)
        except Exception as e:
            return self.view.display_error(str(e))

    def search_perfumes(self, query: str, skip: int = 0, limit: int = 100):
        try:
            if not query:
                return self.get_all_perfumes(skip, limit)

            perfumes = self.repository.search_by_name(name=query, skip=skip, limit=limit)
            perfume_dicts = [self._convert_perfume_to_dict(p) for p in perfumes]
            return self.view.display_search_results(perfume_dicts, query)
        except Exception as e:
            return self.view.display_error(str(e))

    def filter_by_brand(self, brand: str, skip: int = 0, limit: int = 100):
        try:
            perfumes = self.repository.filter_by_brand(brand=brand, skip=skip, limit=limit)
            perfume_dicts = [self._convert_perfume_to_dict(p) for p in perfumes]
            return self.view.display_search_results(perfume_dicts, f"Brand: {brand}")
        except Exception as e:
            return self.view.display_error(str(e))

    def _convert_perfume_to_dict(self, perfume) -> Dict[str, Any]:
        image_url = None
        if perfume.image_path:
            image_url = f"/static/images/perfumes/{os.path.basename(perfume.image_path)}"

        description_preview = None
        if perfume.description:
            description_preview = (perfume.description[:100] + '...') if len(
                perfume.description) > 100 else perfume.description

        return {
            'id': perfume.id,
            'name': perfume.name,
            'brand': perfume.brand,
            'price': perfume.price,
            'description': description_preview,
            'volume_ml': perfume.volume_ml,
            'concentration': perfume.concentration,
            'gender': perfume.gender,
            'image_path': image_url
        }