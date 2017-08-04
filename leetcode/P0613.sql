SELECT MIN(dist) as shortest FROM 
  (SELECT ABS(x1-x2) as dist FROM
   (SELECT t1.x as x1, t2.x as x2 FROM point as t1, point as t2) AS tx) AS ty
   WHERE dist > 0;
