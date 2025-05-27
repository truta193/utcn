from pydantic import BaseModel, Field
from typing import Optional


class PerfumeryBase(BaseModel):
    name: str = Field(..., min_length=1, max_length=100)
    address: str = Field(..., min_length=1, max_length=255)
    city: str = Field(..., min_length=1, max_length=100)
    phone: Optional[str] = Field(None, max_length=20)
    email: Optional[str] = Field(None, max_length=100)
    manager_name: Optional[str] = Field(None, max_length=100)


class PerfumeryCreate(PerfumeryBase):
    pass


class PerfumeryUpdate(BaseModel):
    name: Optional[str] = Field(None, min_length=1, max_length=100)
    address: Optional[str] = Field(None, min_length=1, max_length=255)
    city: Optional[str] = Field(None, min_length=1, max_length=100)
    phone: Optional[str] = Field(None, max_length=20)
    email: Optional[str] = Field(None, max_length=100)
    manager_name: Optional[str] = Field(None, max_length=100)


class PerfumeryInDB(PerfumeryBase):
    id: int

    class Config:
        orm_mode = True


class Perfumery(PerfumeryInDB):
    pass
