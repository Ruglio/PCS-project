import src.IntersectorPolygonLine as IPL


class IPolygonCutter:
    def cut_polygon(self):
        pass

    def get_cutted_polygon(self):
        pass

    def get_intersection_vertices(self):
        pass

    def get_new_points(self):
        pass


class PolygonCutter(IPolygonCutter):
    def __init__(self, intersector: IPL.IIntersectorPolygonLine, polygon: IPL.PLG.IPolygon, segment: IPL.PLG.SG.ISegment):
        self.__intersector = intersector
        self.__polygon = polygon
        self.__cutter = segment

        self.__cutted_polygons = []
        self.__intersectionVertices = []
        self.__new_points = []

    def cut_polygon(self):
        self.__intersectionVertices = self.__intersector.find_intersection_vertices()
        self.__new_points = self.__intersector.find_new_points()
        self.__cutted_polygons = self.__intersector.find_polygons()

        return self.__cutted_polygons

    def get_cutted_polygon(self):
        return self.__cutted_polygons

    def get_new_points(self):
        return self.__new_points

    def get_intersection_vertices(self):
        return self.__intersectionVertices
