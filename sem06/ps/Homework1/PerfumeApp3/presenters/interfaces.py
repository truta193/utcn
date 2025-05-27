from abc import ABC, abstractmethod
from typing import List, Optional, Dict, Any


class PerfumeListViewInterface(ABC):

    @abstractmethod
    def display_perfumes(self, perfumes: List[Dict[str, Any]]) -> None:
        pass

    @abstractmethod
    def display_search_results(self, perfumes: List[Dict[str, Any]], query: str) -> None:
        pass

    @abstractmethod
    def display_error(self, message: str) -> None:
        pass


class PerfumeDetailViewInterface(ABC):

    @abstractmethod
    def display_perfume(self, perfume: Dict[str, Any], availability: List[Dict[str, Any]]) -> None:
        pass

    @abstractmethod
    def show_create_form(self) -> None:
        pass

    @abstractmethod
    def show_edit_form(self, perfume: Dict[str, Any]) -> None:
        pass

    @abstractmethod
    def display_success(self, message: str) -> None:
        pass

    @abstractmethod
    def display_error(self, message: str) -> None:
        pass

    @abstractmethod
    def redirect_to_list(self) -> None:
        pass

    @abstractmethod
    def redirect_to_detail(self, perfume_id: int) -> None:
        pass


class PerfumeryListViewInterface(ABC):

    @abstractmethod
    def display_perfumeries(self, perfumeries: List[Dict[str, Any]]) -> None:
        pass

    @abstractmethod
    def display_error(self, message: str) -> None:
        pass


class PerfumeryDetailViewInterface(ABC):

    @abstractmethod
    def display_perfumery(self, perfumery: Dict[str, Any], inventory: List[Dict[str, Any]]) -> None:
        pass

    @abstractmethod
    def display_filtered_inventory(self, perfumery: Dict[str, Any],
                                   inventory: List[Dict[str, Any]],
                                   filter_description: str) -> None:
        pass

    @abstractmethod
    def show_create_form(self) -> None:
        pass

    @abstractmethod
    def show_edit_form(self, perfumery: Dict[str, Any]) -> None:
        pass

    @abstractmethod
    def display_success(self, message: str) -> None:
        pass

    @abstractmethod
    def display_error(self, message: str) -> None:
        pass

    @abstractmethod
    def redirect_to_list(self) -> None:
        pass

    @abstractmethod
    def redirect_to_detail(self, perfumery_id: int) -> None:
        pass

    @abstractmethod
    def send_export_file(self, file_path: str) -> None:
        pass


class InventoryManagementViewInterface(ABC):

    @abstractmethod
    def show_create_form(self, perfumes: List[Dict[str, Any]], perfumeries: List[Dict[str, Any]]) -> None:
        pass

    @abstractmethod
    def show_edit_form(self, inventory: Dict[str, Any]) -> None:
        pass

    @abstractmethod
    def display_success(self, message: str) -> None:
        pass

    @abstractmethod
    def display_error(self, message: str) -> None:
        pass

    @abstractmethod
    def redirect_to_perfumery(self, perfumery_id: int) -> None:
        pass