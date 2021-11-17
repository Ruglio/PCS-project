from src import PointClass as PC


class ISegment:

    def set_start(self, start: PC.Point):
        pass

    def get_start(self):
        pass

    def set_end(self, end: PC.Point):
        pass

    def get_end(self):
        pass

    def set_segment(self, start: PC.Point, end: PC.Point):
        pass

    def compute_tangent(self):
        pass

    def get_tangent(self):
        pass


class Segment(ISegment):

    def __init__(self, start: PC.Point, end: PC.Point):
        self.__start = start
        self.__end = end
        self.__tangent = end.get_coordinates() - start.get_coordinates()

    def set_start(self, start: PC.Point):
        self.__start = start

    def get_start(self):
        return self.__start

    def set_end(self, end: PC.Point):
        self.__end = end

    def get_end(self):
        return self.__end

    def set_segment(self, start: PC.Point, end: PC.Point):
        self.__start = start
        self.__end = end

    def compute_tangent(self):
        self.__tangent = (self.__end - self.__start).get_coordinates()
        return self.__tangent

    def get_tangent(self):
        return self.__tangent

    def __eq__(self, other):
        return (self.get_start() == other.get_start()) and (self.get_end() == other.get_end())
