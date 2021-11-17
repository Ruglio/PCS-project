from src import CONSTANT
import numpy as np
import numpy.linalg as nalg
import math
from enum import Enum


class Type(Enum):
    NoIntersection = 0
    IntersectionOnLine = 1
    IntersectionOnSegment = 2
    IntersectionParallelOnLine = 3
    IntersectionParallelOnSegment = 4


class Position(Enum):
    Begin = 0
    Inner = 1
    End = 2
    Outer = 3


class IIntersector1D1D:
    def set_first_segment(self, origin, end):
        pass

    def set_second_segment(self, origin, end):
        pass

    def compute_intersection(self):
        pass

    def parametric_coordinates(self):
        pass

    def first_parametric_coordinate(self):
        pass

    def second_parametric_coordinate(self):
        pass

    def position_intersection_in_first_segment(self):
        pass

    def position_intersection_in_second_segment(self):
        pass

    def type_intersection(self):
        pass

    def intersection_first_parametric_coordinate(self, origin, end):
        pass

    def intersection_second_parametric_coordinate(self, origin, end):
        pass


class Intersector1D1D(IIntersector1D1D):
    def __init__(self):
        self.__type = Type.NoIntersection
        self.__positionIntersectionFirstEdge = Position.Begin
        self.__positionIntersectionSecondEdge = Position.Begin
        self.__resultParametricCoordinates = np.array([0, 0])
        self.__originFirstSegment = np.array([0, 0])
        self.__rightHandSide = np.array([0, 0])
        self.__matrixTangentVector = np.zeros((2, 2))

    def set_first_segment(self, origin, end):
        self.__matrixTangentVector[:, 0] = end - origin
        self.__originFirstSegment = origin

    def set_second_segment(self, origin, end):
        self.__matrixTangentVector[:, 1] = origin - end
        self.__rightHandSide = origin - self.__originFirstSegment

    def parametric_coordinates(self):
        return self.__resultParametricCoordinates

    def first_parametric_coordinate(self):
        return self.__resultParametricCoordinates[0]

    def second_parametric_coordinate(self):
        return self.__resultParametricCoordinates[1]

    def position_intersection_in_first_segment(self):
        return self.__positionIntersectionFirstEdge

    def position_intersection_in_second_segment(self):
        return self.__positionIntersectionSecondEdge

    def type_intersection(self):
        return self.__type

    def intersection_first_parametric_coordinate(self, origin, end):
        return (1 - self.__resultParametricCoordinates[0]) * origin + self.__resultParametricCoordinates[0] * end

    def intersection_second_parametric_coordinate(self, origin, end):
        return (1 - self.__resultParametricCoordinates[1]) * origin + self.__resultParametricCoordinates[1] * end

    def compute_intersection(self):
        parallelism = nalg.det(self.__matrixTangentVector)
        self.__type = Type.NoIntersection
        intersection = False
        check = CONSTANT.INTERSECTION_TOLERANCE * CONSTANT.INTERSECTION_TOLERANCE * nalg.norm(
            self.__matrixTangentVector[:, 0]) * nalg.norm(self.__matrixTangentVector[:, ])

        if parallelism * parallelism >= check:
            solverMatrix = np.array([[self.__matrixTangentVector[1, 1], -self.__matrixTangentVector[0, 1]],
                                     [-self.__matrixTangentVector[1, 0], self.__matrixTangentVector[0, 0]]])

            self.__resultParametricCoordinates = np.dot(solverMatrix, self.__rightHandSide)
            self.__resultParametricCoordinates /= parallelism

            if (self.__resultParametricCoordinates[1] > -CONSTANT.INTERSECTION_TOLERANCE and
                    self.__resultParametricCoordinates[1] - 1.0 < CONSTANT.INTERSECTION_TOLERANCE):
                self.__type = Type.IntersectionOnLine
                intersection = True

                if (self.__resultParametricCoordinates[0] > -CONSTANT.INTERSECTION_TOLERANCE and
                        self.__resultParametricCoordinates[0] - 1.0 < CONSTANT.INTERSECTION_TOLERANCE):
                    self.__type = Type.IntersectionOnSegment

        else:
            parallelism2 = math.fabs(
                self.__matrixTangentVector[0, 0] * self.__rightHandSide[1] - self.__rightHandSide[0] *
                self.__matrixTangentVector[1, 0])
            squaredNormFirstEdge = np.square(nalg.norm(self.__matrixTangentVector[:, 0]))
            check2 = CONSTANT.INTERSECTION_TOLERANCE * CONSTANT.INTERSECTION_TOLERANCE * squaredNormFirstEdge * nalg.norm(
                self.__rightHandSide)
            if (parallelism2 * parallelism2 <= check2):
                tempNorm = 1.0 / squaredNormFirstEdge
                self.__resultParametricCoordinates[0] = np.dot(self.__matrixTangentVector[:, 0], self.__rightHandSide)
                self.__resultParametricCoordinates[1] = self.__resultParametricCoordinates[0] - np.dot(
                    self.__matrixTangentVector[:, 0], self.__matrixTangentVector[:, 1])
                self.__resultParametricCoordinates = tempNorm * self.__resultParametricCoordinates
                intersection = True
                self.__type = Type.IntersectionParallelOnLine

                if (self.__resultParametricCoordinates[1] < self.__resultParametricCoordinates[0]):
                    tmp = self.__resultParametricCoordinates[0]
                    self.__resultParametricCoordinates[0] = self.__resultParametricCoordinates[1]
                    self.__resultParametricCoordinates[1] = tmp

                if ((self.__resultParametricCoordinates[0] > -CONSTANT.INTERSECTION_TOLERANCE and
                     self.__resultParametricCoordinates[0] - 1.0 < CONSTANT.INTERSECTION_TOLERANCE) or (
                        self.__resultParametricCoordinates[1] > -CONSTANT.INTERSECTION_TOLERANCE and
                        self.__resultParametricCoordinates[1] - 1.0 < CONSTANT.INTERSECTION_TOLERANCE)):
                    self.__type = Type.IntersectionParallelOnSegment

                else:
                    if (self.__resultParametricCoordinates[0] < CONSTANT.INTERSECTION_TOLERANCE and
                            self.__resultParametricCoordinates[
                                1] - 1.0 > -CONSTANT.INTERSECTION_TOLERANCE):
                        self.__type = Type.IntersectionParallelOnSegment

        if (self.__resultParametricCoordinates[0] < -CONSTANT.INTERSECTION_TOLERANCE or
                self.__resultParametricCoordinates[0] - 1.0 > CONSTANT.INTERSECTION_TOLERANCE):
            self.__positionIntersectionFirstEdge = Position.Outer

        elif ((self.__resultParametricCoordinates[0] > -CONSTANT.INTERSECTION_TOLERANCE) and (
                self.__resultParametricCoordinates[0] < CONSTANT.INTERSECTION_TOLERANCE)):
            self.__resultParametricCoordinates[0] = 0.0
            self.__positionIntersectionFirstEdge = Position.Begin

        elif ((self.__resultParametricCoordinates[0] > 1.0 - CONSTANT.INTERSECTION_TOLERANCE) and (
                self.__resultParametricCoordinates[0] < 1.0 + CONSTANT.INTERSECTION_TOLERANCE)):
            self.__resultParametricCoordinates[0] = 1.0
            self.__positionIntersectionFirstEdge = Position.End

        else:
            self.__positionIntersectionFirstEdge = Position.Inner

        if (self.__resultParametricCoordinates[1] < -CONSTANT.INTERSECTION_TOLERANCE or
                self.__resultParametricCoordinates[1] > 1.0 + CONSTANT.INTERSECTION_TOLERANCE):
            self.__positionIntersectionSecondEdge = Position.Outer

        elif ((self.__resultParametricCoordinates[1] > -CONSTANT.INTERSECTION_TOLERANCE) and (
                self.__resultParametricCoordinates[1] < CONSTANT.INTERSECTION_TOLERANCE)):
            self.__resultParametricCoordinates[1] = 0.0
            self.__positionIntersectionSecondEdge = Position.Begin

        elif ((self.__resultParametricCoordinates[1] > 1.0 - CONSTANT.INTERSECTION_TOLERANCE) and (
                self.__resultParametricCoordinates[1] < 1.0 + CONSTANT.INTERSECTION_TOLERANCE)):
            self.__resultParametricCoordinates[1] = 1.0
            self.__positionIntersectionSecondEdge = Position.End

        else:
            self.__positionIntersectionSecondEdge = Position.Inner

        return intersection
