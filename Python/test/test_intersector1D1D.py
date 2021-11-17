from unittest import TestCase
from src import Intersector1D1D


class TestIntersector1D1D(TestCase):
    def test_parallel_intersection(self):
        a = Intersector1D1D.np.array([0, 0])
        b = Intersector1D1D.np.array([4, 0])
        c = Intersector1D1D.np.array([1, 0])
        d = Intersector1D1D.np.array([2, 0])

        intersector = Intersector1D1D.Intersector1D1D()

        try:
            intersector.set_first_segment(a, b)
            intersector.set_second_segment(c, d)
        except Exception as ex:
            self.fail()

        try:
            self.assertTrue(intersector.compute_intersection())
            self.assertEqual(intersector.type_intersection(), Intersector1D1D.Type.IntersectionParallelOnSegment)
            self.assertAlmostEqual(0.5, intersector.second_parametric_coordinate())
            self.assertAlmostEqual(0.25, intersector.first_parametric_coordinate())
        except Exception as ex:
            self.fail()


    def test_segment_intersection(self):
        a = Intersector1D1D.np.array([1, 0])
        b = Intersector1D1D.np.array([5, 0])
        c = Intersector1D1D.np.array([3, -6])
        d = Intersector1D1D.np.array([3, 6])

        intersector = Intersector1D1D.Intersector1D1D()

        try:
            intersector.set_first_segment(a, b)
            intersector.set_second_segment(c, d)
        except Exception as ex:
            self.fail()

        try:
            self.assertTrue(intersector.compute_intersection())
            self.assertEqual(intersector.type_intersection(), Intersector1D1D.Type.IntersectionOnSegment)
            self.assertAlmostEqual(0.5, intersector.first_parametric_coordinate())
            self.assertAlmostEqual(0.5, intersector.second_parametric_coordinate())
            self.assertLessEqual(intersector.first_parametric_coordinate(), 1.0)
            self.assertGreaterEqual(intersector.first_parametric_coordinate(), 0.0)
        except Exception as ex:
            self.fail()

    def test_on_line_intersection(self):
        a = Intersector1D1D.np.array([3, 6])
        b = Intersector1D1D.np.array([3, 2])
        c = Intersector1D1D.np.array([5, 0])
        d = Intersector1D1D.np.array([1, 0])

        intersector = Intersector1D1D.Intersector1D1D()

        try:
            intersector.set_first_segment(a, b)
            intersector.set_second_segment(c, d)
        except Exception as ex:
            self.fail()

        try:
            self.assertTrue(intersector.compute_intersection())
            self.assertEqual(intersector.type_intersection(), Intersector1D1D.Type.IntersectionOnLine)
            self.assertAlmostEqual(1.5, intersector.first_parametric_coordinate())
            self.assertAlmostEqual(0.5, intersector.second_parametric_coordinate())
            self.assertGreaterEqual(intersector.first_parametric_coordinate(), 1.0)
        except Exception as ex:
            self.fail()









