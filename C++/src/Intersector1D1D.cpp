#include "Intersector1D1D.hpp"

Intersector1D1D::Intersector1D1D()
{
  type = Intersector1D1D::NoIntersection;
  resultParametricCoordinates.setZero(2);
}

// ***************************************************************************
bool Intersector1D1D::ComputeIntersection()
{
  // parallelism is the wedge product of the 2 tangent vectors, so analyzing it we can say if they are parallel
  double parallelism = matrixTangentVector.determinant();
  type = NoIntersection;
  bool intersection = false;

  // check is used to not use square root function and division, lowering the computational cost. In fact we are controlling if the wedge product
  // divided by the squared norms of the two tangent vectors multiplied is greater than squared parallelism
  double check = INTERSECTION_TOLERANCE * INTERSECTION_TOLERANCE * matrixTangentVector.col(0).squaredNorm() *  matrixTangentVector.col(1).squaredNorm();
  //checking if the vectors are not parallel
  if(parallelism * parallelism >= check)
  {
    Matrix2d solverMatrix;
    //inverting the matrix made up by the 2 tangent vectors multiplied by the determinant
    solverMatrix << matrixTangentVector(1,1), -matrixTangentVector(0,1), -matrixTangentVector(1,0), matrixTangentVector(0,0);
    /// <li> If the edge and the trace are not parallel look for the intersection with parametric coordinates
    resultParametricCoordinates = solverMatrix * rightHandSide;
    //dividing by the determinant here because we are computing only 2 divisions
    resultParametricCoordinates /= parallelism;
    //checking if the parametric coordinates of the second segment is inside the segment itself
    if (resultParametricCoordinates(1) > -INTERSECTION_TOLERANCE  && resultParametricCoordinates(1)-1.0 < INTERSECTION_TOLERANCE)
    {
      //now we can say that there is intersection because the line of the first segment intersect the second segment and thus the intesection
      //is at least "IntersectionOnLine"
      type = IntersectionOnLine;
      intersection = true;
      //checking if the parametric coordinates of the intersection, in respect to the first segment, is inside the segment itself
      if (resultParametricCoordinates(0) > -INTERSECTION_TOLERANCE  && resultParametricCoordinates(0)-1.0 < INTERSECTION_TOLERANCE)
        //if it is true the intersection is inside the segment
        type = IntersectionOnSegment;
    }
  }
  //if they are parallel
  else
  {
    //parallelism2 is the wedge product between the tangent vector of the first segment and the vector made up of (origin of the second segment) - (origin of the first segment),represented by rightHandSide
    //parallelism2 is used to control if the segments are on the same line: if the wedge product is 0 we can say that they are parallel on the same line because
    //rightHandSide will be equal to (0,0), whereas in the other case it will be different from 0
    double parallelism2 = fabs(matrixTangentVector(0,0) * rightHandSide.y() - rightHandSide.x() * matrixTangentVector(1,0));
    /// <li> In case of parallelism check if the segment is the same with parametric coordinates

    double squaredNormFirstEdge = matrixTangentVector.col(0).squaredNorm();
    //check 2 is used just like the previous check
    double check2 = INTERSECTION_TOLERANCE * INTERSECTION_TOLERANCE * squaredNormFirstEdge * rightHandSide.squaredNorm();
    //checking if the segments are on the same line, if not there is "NoIntersection"
    if( parallelism2 * parallelism2 <= check2 )
    {
      //dividing here to reduce computational cost
      double tempNorm = 1.0/squaredNormFirstEdge;
      //inverting the tangent vector to solve the system for the first parametric coordinate
      resultParametricCoordinates(0) = matrixTangentVector.col(0).dot(rightHandSide) * tempNorm ;
      // solving for the second parametric coordinate
      resultParametricCoordinates(1) = resultParametricCoordinates(0) - matrixTangentVector.col(0).dot(matrixTangentVector.col(1)) * tempNorm;
      // we know that there is intersection
      intersection = true;
      type = IntersectionParallelOnLine;

      //swapping in order to have ascending order
      if(resultParametricCoordinates(1) < resultParametricCoordinates(0))
      {
        double tmp = resultParametricCoordinates(0);
        resultParametricCoordinates(0) = resultParametricCoordinates(1);
        resultParametricCoordinates(1) = tmp;
      }
      // if one vertex is in the edge there is the intersection
      if( (resultParametricCoordinates(0) > -INTERSECTION_TOLERANCE && resultParametricCoordinates(0)-1.0 < INTERSECTION_TOLERANCE) ||
          (resultParametricCoordinates(1) > -INTERSECTION_TOLERANCE && resultParametricCoordinates(1)-1.0 <INTERSECTION_TOLERANCE)   )
        type = IntersectionParallelOnSegment;
      else
      {
        //IL PRIMO SEGMENTO DATO IN INPUT E' CONTENUTO NEL SECONDO O VICEVERSA
        if( ( resultParametricCoordinates(0) < INTERSECTION_TOLERANCE && resultParametricCoordinates(1) - 1.0 > -INTERSECTION_TOLERANCE) )
          type = IntersectionParallelOnSegment;
      }
    }
  }
  /// </ul>
  if(resultParametricCoordinates(0) < -INTERSECTION_TOLERANCE || resultParametricCoordinates(0) > 1.0 + INTERSECTION_TOLERANCE)
    positionIntersectionFirstEdge =  Outer;
  else if((resultParametricCoordinates(0) > -INTERSECTION_TOLERANCE) && (resultParametricCoordinates(0) < INTERSECTION_TOLERANCE))
  {
    resultParametricCoordinates(0) = 0.0;
    positionIntersectionFirstEdge = Begin;
  }
  else if ((resultParametricCoordinates(0) > 1.0 - INTERSECTION_TOLERANCE) && (resultParametricCoordinates(0) < 1.0 +INTERSECTION_TOLERANCE))
  {
    resultParametricCoordinates(0) = 1.0;
    positionIntersectionFirstEdge = End;
  }
  else
    positionIntersectionFirstEdge = Inner;

  if(resultParametricCoordinates(1) < -INTERSECTION_TOLERANCE || resultParametricCoordinates(1) > 1.0 + INTERSECTION_TOLERANCE)
    positionIntersectionSecondEdge =  Outer;
  else if((resultParametricCoordinates(1) > -INTERSECTION_TOLERANCE) && (resultParametricCoordinates(1) < INTERSECTION_TOLERANCE))
  {
    resultParametricCoordinates(1) = 0.0;
    positionIntersectionSecondEdge = Begin;
  }
  else if ((resultParametricCoordinates(1) > 1.0 - INTERSECTION_TOLERANCE) && (resultParametricCoordinates(1) < 1.0 + INTERSECTION_TOLERANCE))
  {
    resultParametricCoordinates(1) = 1.0;
    positionIntersectionSecondEdge = End;
  }
  else
    positionIntersectionSecondEdge = Inner;

  return intersection;
}
