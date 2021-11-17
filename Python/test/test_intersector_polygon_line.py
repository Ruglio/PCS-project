from unittest import TestCase
import src.IntersectorPolygonLine as IPL
import src.Intersector1D1D as INTSEC


class TestIntersectorPolygonLine(TestCase):
    def test_find_intersection_vertices(self):

        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)

        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.1, 5.9]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = IPL.INTSEC.Intersector1D1D()

        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)

        try:
            intersection_points = intersector.find_intersection_vertices()
            self.assertEqual(4, len(intersection_points))
        except Exception as ex:
            self.fail()

    def test_find_polygons_1a(self):
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.1, 5.9]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()
        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()
        try:
            self.assertEqual(8, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(10, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[1].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()
        try:
            self.assertEqual(11, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(7, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(10, new_extended_polygons[0].get_point_label_at_position(5))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(6))
            self.assertEqual(9, new_extended_polygons[0].get_point_label_at_position(7))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(8))
            self.assertEqual(8, new_extended_polygons[0].get_point_label_at_position(9))

            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(10, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(7, new_extended_polygons[1].get_point_label_at_position(2))
            self.assertEqual(11, new_extended_polygons[1].get_point_label_at_position(3))

            self.assertEqual(5, new_extended_polygons[2].get_point_label_at_position(0))
            self.assertEqual(8, new_extended_polygons[2].get_point_label_at_position(1))
            self.assertEqual(6, new_extended_polygons[2].get_point_label_at_position(2))
            self.assertEqual(9, new_extended_polygons[2].get_point_label_at_position(3))
        except Exception as ex:
            self.fail()

    def test_find_polygon_1b(self):     #same polygon with swapped point in the segment
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.1, 5.9]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()
        try:
            self.assertEqual(8, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(10, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[1].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(8, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(9, new_extended_polygons[0].get_point_label_at_position(5))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(6))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(10, new_extended_polygons[0].get_point_label_at_position(7))
            self.assertEqual(7, new_extended_polygons[0].get_point_label_at_position(8))
            self.assertEqual(11, new_extended_polygons[0].get_point_label_at_position(9))

            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(9, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(6, new_extended_polygons[1].get_point_label_at_position(2))
            self.assertEqual(8, new_extended_polygons[1].get_point_label_at_position(3))

            self.assertEqual(5, new_extended_polygons[2].get_point_label_at_position(0))
            self.assertEqual(11, new_extended_polygons[2].get_point_label_at_position(1))
            self.assertEqual(7, new_extended_polygons[2].get_point_label_at_position(2))
            self.assertEqual(10, new_extended_polygons[2].get_point_label_at_position(3))
        except Exception as ex:
            self.fail()

    def test_find_polygons_1c(self):   # start/end point consecutive
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.1, 5.9]))
        p3 = p1.get_coordinates() * 0.9 + p2.get_coordinates() * 0.1
        end = IPL.PLG.SG.PC.Point(p3)
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(8, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(10, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(3, new_extended_polygons[1].get_number_vertices())
            self.assertEqual(5, new_extended_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(11, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(10, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(5))
            self.assertEqual(9, new_extended_polygons[0].get_point_label_at_position(6))
            self.assertEqual(7, new_extended_polygons[0].get_point_label_at_position(7))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(8))
            self.assertEqual(8, new_extended_polygons[0].get_point_label_at_position(9))

            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(10, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(11, new_extended_polygons[1].get_point_label_at_position(2))

            self.assertEqual(5, new_extended_polygons[2].get_point_label_at_position(0))
            self.assertEqual(8, new_extended_polygons[2].get_point_label_at_position(1))
            self.assertEqual(6, new_extended_polygons[2].get_point_label_at_position(2))
            self.assertEqual(7, new_extended_polygons[2].get_point_label_at_position(3))
            self.assertEqual(9, new_extended_polygons[2].get_point_label_at_position(4))
        except Exception as ex:
            self.fail()

    def test_find_polygons_1d(self):    #start in, end out
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 3.7]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.06, 4.81]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(8, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(9, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(3, new_extended_polygons[1].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(11, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(10, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(5))
            self.assertEqual(9, new_extended_polygons[0].get_point_label_at_position(6))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(7))
            self.assertEqual(8, new_extended_polygons[0].get_point_label_at_position(8))

            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(10, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(11, new_extended_polygons[1].get_point_label_at_position(2))

            self.assertEqual(5, new_extended_polygons[2].get_point_label_at_position(0))
            self.assertEqual(8, new_extended_polygons[2].get_point_label_at_position(1))
            self.assertEqual(6, new_extended_polygons[2].get_point_label_at_position(2))
            self.assertEqual(9, new_extended_polygons[2].get_point_label_at_position(3))
        except Exception as ex:
            self.fail()

    def test_find_polygons_1e(self):     #start out, end out
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.6, 1.5]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.5, 4.8]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 6.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.2, 4.2]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.06, 4.81]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.8, 6.1]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(8, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(8, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(3, new_extended_polygons[1].get_number_vertices())
            self.assertEqual(3, new_extended_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(11, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(10, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(5))
            self.assertEqual(9, new_extended_polygons[0].get_point_label_at_position(6))
            self.assertEqual(8, new_extended_polygons[0].get_point_label_at_position(7))

            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(10, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(11, new_extended_polygons[1].get_point_label_at_position(2))

            self.assertEqual(5, new_extended_polygons[2].get_point_label_at_position(0))
            self.assertEqual(8, new_extended_polygons[2].get_point_label_at_position(1))
            self.assertEqual(9, new_extended_polygons[2].get_point_label_at_position(2))
        except Exception as ex:
            self.fail()

    def  test_find_polygons_2a(self):      #pentagon
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 2.1]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.4, 4.2]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.6, 4.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 2.1]))

        polygonvertices = [p0, p1, p2, p3, p4]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.4, 2.75]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.6, 2.2]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(4, new_polygons[0].get_number_vertices())
            self.assertEqual(4, new_polygons[1].get_number_vertices())
            self.assertEqual(6, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(6, new_extended_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(0, new_extended_polygons[0].get_point_label_at_position(0))
            self.assertEqual(1, new_extended_polygons[0].get_point_label_at_position(1))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(2))
            self.assertEqual(5, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(7, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(5))

            self.assertEqual(1, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(2, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(2))
            self.assertEqual(7, new_extended_polygons[1].get_point_label_at_position(3))
            self.assertEqual(5, new_extended_polygons[1].get_point_label_at_position(4))
            self.assertEqual(6, new_extended_polygons[1].get_point_label_at_position(5))
        except Exception as ex:
            self.fail()

    def test_find_polygons_2b(self):    #pentagon with segment passing through 2 vertices
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.5, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 2.1]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.4, 4.2]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.6, 4.2]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 2.1]))

        polygonvertices = [p0, p1, p2, p3, p4]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 2.1]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.0, 2.1]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(3, new_polygons[0].get_number_vertices())
            self.assertEqual(4, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(4, new_extended_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(0, new_extended_polygons[0].get_point_label_at_position(0))
            self.assertEqual(1, new_extended_polygons[0].get_point_label_at_position(1))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(2))

            self.assertEqual(1, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(2, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(3, new_extended_polygons[1].get_point_label_at_position(2))
            self.assertEqual(4, new_extended_polygons[1].get_point_label_at_position(3))
        except Exception as ex:
            self.fail()

    def test_find_polygons_3(self): # professore D'Auria's test polygon
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([8.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.64, 1.5]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([8.93, 4.48]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.18, 5.36]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.52, 9.22]))
        p6 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 5.0]))
        p7 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([6.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5, p6, p7]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([7.28, -0.72]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.2, 9.14]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(5, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(6, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(6, new_polygons[2].get_number_vertices())
            self.assertEqual(6, new_polygons[3].get_number_vertices())
            self.assertEqual(3, new_polygons[4].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_4(self):   # professore D'Auria's test polygon with segment that ends on a vertex
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([8.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.64, 1.5]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([8.93, 4.48]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.18, 5.36]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.52, 9.22]))
        p6 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 5.0]))
        p7 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([6.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5, p6, p7]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([7.28, -0.72]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.52, 9.22])) #corresponding to polygon_vertices[5]
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(3, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(10, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_5(self):     #square test with segment.end outside
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 4.0]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 5.0]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.0, 1.0]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(5, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_5b(self):  #square test with segment.end inside
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 4.0]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.48, 3.03]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.03, 3.63]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(5, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_5c(self):      #square test with segment.start inside and segment.end outside
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 4.0]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.03, 3.63]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 5.0]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(5, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_5d(self):    #square test with segment.start inside and segment.end outside
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 0.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 4.0]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 4.0]))

        polygonvertices = [p0, p1, p2, p3]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.48, 3.03]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.0, 1.0]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(5, new_polygons[0].get_number_vertices())
            self.assertEqual(3, new_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_find_polygons_6(self):      #rectangle
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 1.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.0, 1.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([5.0, 3.1]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([1.0, 3.1]))

        polygonvertices = [p0, p1, p2, p3]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, 1.2]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 3.0]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(2, len(new_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(4, new_polygons[0].get_number_vertices())
            self.assertEqual(4, new_polygons[1].get_number_vertices())
            self.assertEqual(6, new_extended_polygons[0].get_number_vertices())
            self.assertEqual(6, new_extended_polygons[1].get_number_vertices())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(0, new_extended_polygons[0].get_point_label_at_position(0))
            self.assertEqual(6, new_extended_polygons[0].get_point_label_at_position(1))
            self.assertEqual(4, new_extended_polygons[0].get_point_label_at_position(2))
            self.assertEqual(5, new_extended_polygons[0].get_point_label_at_position(3))
            self.assertEqual(7, new_extended_polygons[0].get_point_label_at_position(4))
            self.assertEqual(3, new_extended_polygons[0].get_point_label_at_position(5))

            self.assertEqual(1, new_extended_polygons[1].get_point_label_at_position(0))
            self.assertEqual(2, new_extended_polygons[1].get_point_label_at_position(1))
            self.assertEqual(7, new_extended_polygons[1].get_point_label_at_position(2))
            self.assertEqual(5, new_extended_polygons[1].get_point_label_at_position(3))
            self.assertEqual(4, new_extended_polygons[1].get_point_label_at_position(4))
            self.assertEqual(6, new_extended_polygons[1].get_point_label_at_position(5))
        except Exception as ex:
            self.fail()

    # professor D'Auria's polygon test
    def test_find_polygons_7(self):    #professor D'Auria's polygon test
        p0 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([2.0, -2.0]))
        p1 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, -1.0]))
        p2 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.0, 1.0]))
        p3 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 2.0]))
        p4 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.0, 2.0]))
        p5 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([3.0, 3.0]))
        p6 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([-1.0, 3.0]))
        p7 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([-3.0, 1.0]))
        p8 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([0.0, 0.0]))
        p9 = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([-3.0, -2.0]))

        polygonvertices = [p0, p1, p2, p3, p4, p5, p6, p7, p8, p9]
        polygon = IPL.PLG.Polygon(polygonvertices)
        start = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([-4.0, -4.0]))
        end = IPL.PLG.SG.PC.Point(IPL.INTSEC.np.array([4.0, 4.0]))
        segment = IPL.PLG.SG.Segment(start, end)

        intersector1d1d = INTSEC.Intersector1D1D()
        intersector = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        intersection_points = intersector.find_intersection_vertices()
        new_polygons = intersector.find_polygons()
        new_points = intersector.find_new_points()
        new_extended_polygons = intersector.get_extended_polygons()

        try:
            self.assertEqual(4, len(new_polygons))
        except Exception as ex:
            self.fail()
        try:
            self.assertEqual(6, new_polygons[0].get_number_vertices())
            self.assertEqual(7, new_polygons[1].get_number_vertices())
            self.assertEqual(3, new_polygons[2].get_number_vertices())
            self.assertEqual(3, new_polygons[3].get_number_vertices())
        except Exception as ex:
            self.fail()