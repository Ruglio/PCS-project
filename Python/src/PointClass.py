import numpy as np
from src import CONSTANT


class Point:
    def __init__(self, coordinates):
        self.__coordinates = coordinates
        self.__label = -2

    def set_coordinates(self, x: float, y: float):
        self.__coordinates = np.array([x, y])

    def get_coordinates(self):
        return self.__coordinates

    def set_point_label(self, label):
        self.__label = label

    def get_point_label(self):
        return self.__label

    def __add__(self, other):
        return Point(self.__coordinates + other.__coordinates)

    def __sub__(self, other):
        return Point(self.__coordinates - other.__coordinates)

    def __eq__(self, other):
        return np.linalg.norm(self.__coordinates - other.__coordinates) < CONSTANT.POINT_TOLERANCE

    def __ne__(self, other):
        return not (self == other)

    def __lt__(self, other):
        return self.__label < other.__label


