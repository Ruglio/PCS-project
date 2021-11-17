from unittest import TestCase

import src.PolygonCutter as POLCUT
import src.IntersectorPolygonLine as IPL


class TestPolygonCutter(TestCase):
    def test_cut_polygon(self):
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

        intersector1d1d = IPL.INTSEC.Intersector1D1D()
        intersector_polygon_line = IPL.intersector_polygon_line(intersector1d1d, polygon, segment)
        polygon_cutter = POLCUT.PolygonCutter(intersector_polygon_line, polygon, segment)

        polygon_cutter.cut_polygon()
        cutted_polygons = polygon_cutter.get_cutted_polygon()

        try:
            self.assertEqual(4, len(cutted_polygons))
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(6, cutted_polygons[0].get_number_vertices())
            self.assertEqual(7, cutted_polygons[1].get_number_vertices())
            self.assertEqual(3, cutted_polygons[2].get_number_vertices())
            self.assertEqual(3, cutted_polygons[3].get_number_vertices())
        except Exception as ex:
            self.fail()
