from unittest import TestCase
import src.PolygonClass as PLG
import src.PointClass as PC
import src.SegmentClass as SG
import numpy as np


class TestPolygonClass(TestCase):
    def test_setter_getter_methods(self):

        p0 = PC.Point(np.array([1, 2]))
        p1 = PC.Point(np.array([3, 2]))
        p2 = PC.Point(np.array([2, 6]))

        vertices = [p0, p1, p2]

        edges = [SG.Segment(p0, p1), SG.Segment(p1, p2), SG.Segment(p2, p0)]

        try:
            polygon = PLG.Polygon(vertices)
            self.assertEqual(3, polygon.get_number_vertices())
        except Exception as ex:
            self.fail()
        try:
            self.assertEqual(polygon.get_vertices(), vertices)
        except Exception as ex:
            self.fail()

        p3 = PC.Point(np.array([3.5, 2.3]))
        p4 = PC.Point(np.array([2.2, 3.4]))
        p5 = PC.Point(np.array([2.5, 3.4]))

        try:
            polygon.set_vertex_at_position(p3, 2)
            polygon.set_vertex_at_position(p4, 1)
            polygon.set_vertex_at_position(p5, 0)
            self.assertEqual(p3, polygon.get_vertices()[2])
            self.assertEqual(p4, polygon.get_vertices()[1])
            self.assertEqual(p5, polygon.get_vertices()[0])
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(p3, polygon.get_vertex_at_position(2))
            self.assertEqual(p4, polygon.get_vertex_at_position(1))
            self.assertEqual(p5, polygon.get_vertex_at_position(0))
            self.assertEqual(p3, polygon.get_last_vertex())
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(edges, polygon.get_edges())
        except Exception as ex:
            self.fail()
        id = 3
        try:
            polygon.next_vertex_id(id)
            self.fail()
        except Exception as ex:
            self.assertEqual("Vertex id is not present", str(ex))

        id = 2

        try:
            self.assertEqual(0, polygon.next_vertex_id(id))
        except Exception as ex:
            self.fail()

        id = 0

        try:
            self.assertEqual(1, polygon.next_vertex_id(id))
        except Exception as ex:
            self.fail()



    def test_insertion_method(self):
        p0 = PC.Point(np.array([1, 2]))
        p1 = PC.Point(np.array([3, 2]))
        p2 = PC.Point(np.array([2, 6]))

        vertices = [p0, p1, p2]

        polygon = PLG.Polygon(vertices)
        p3 = PC.Point(np.array([1.5,3.8]))

        try:
            polygon.append_vertex(p3)
            self.assertEqual(p3, polygon.get_vertices()[3])
            self.assertEqual(4, polygon.get_number_vertices())
        except Exception as ex:
            self.fail()

        p4 = PC.Point(np.array([2.2,1.8]))

        try:
            polygon.insert_vertex_at_position(p4, 1)
            self.assertEqual(p0, polygon.get_vertex_at_position(0))
            self.assertEqual(p4, polygon.get_vertex_at_position(1))
            self.assertEqual(p1, polygon.get_vertex_at_position(2))
            self.assertEqual(p2, polygon.get_vertex_at_position(3))
            self.assertEqual(p3, polygon.get_vertex_at_position(4))
            self.assertEqual(5, polygon.get_number_vertices())
        except Exception as ex:
            self.fail()

    def test_labels_method(self):
        p0 = PC.Point(np.array([1, 2]))
        p1 = PC.Point(np.array([3, 2]))
        p2 = PC.Point(np.array([2, 6]))

        vertices = [p0, p1, p2]
        polygon = PLG.Polygon(vertices)

        try:
            polygon.set_default_vertices_label()
            self.assertEqual(0, polygon.get_vertex_at_position(0).get_point_label())
            self.assertEqual(1, polygon.get_vertex_at_position(1).get_point_label())
            self.assertEqual(2, polygon.get_vertex_at_position(2).get_point_label())
        except Exception as ex:
            self.fail()

        try:
            polygon.set_vertex_label_at_position(0, 1)
            self.assertEqual(1, polygon.get_point_label_at_position(0))
        except Exception as ex:
            self.fail()

        vector = [3, 5, 7]

        try:
            polygon.set_vertices_label(vector)
            self.assertEqual(3, polygon.get_vertex_at_position(0).get_point_label())
            self.assertEqual(5, polygon.get_vertex_at_position(1).get_point_label())
            self.assertEqual(7, polygon.get_vertex_at_position(2).get_point_label())
        except Exception as ex:
            self.fail()





