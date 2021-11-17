from unittest import TestCase
import src.SegmentClass as SG


class TestSegmentClass(TestCase):
    def test_setter_getter_methods(self):
        start = SG.PC.Point(SG.PC.np.array([1, 2]))
        end = SG.PC.Point(SG.PC.np.array([2, 3]))
        segment = SG.Segment(SG.PC.Point(SG.PC.np.array([0, 0])), SG.PC.Point(SG.PC.np.array([0, 0])))

        try:
            segment.set_start(start)
            segment.set_end(end)
        except Exception as ex:
            self.fail()

        try:
            self.assertEqual(start, segment.get_start())
            self.assertEqual(end, segment.get_end())
        except Exception as ex:
            self.fail()

        segment = SG.Segment(SG.PC.Point(SG.PC.np.array([0, 0])), SG.PC.Point(SG.PC.np.array([0, 0])))
        try:
            segment.set_segment(start, end)
            self.assertEqual(start, segment.get_start())
            self.assertEqual(end, segment.get_end())
        except Exception as ex:
            self.fail()

    def test_tangent_method(self):
        start = SG.PC.Point(SG.PC.np.array([1, 2]))
        end = SG.PC.Point(SG.PC.np.array([2, 3]))
        segment = SG.Segment(start, end)
        tangent = SG.PC.np.array([1,1])

        try:
            SG.PC.np.testing.assert_array_equal(tangent, segment.compute_tangent())
        except Exception as ex:
            self.fail()

        try:
            SG.PC.np.testing.assert_array_equal(tangent, segment.get_tangent())
        except Exception as ex:
            self.fail()

