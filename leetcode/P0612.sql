SELECT CAST(MIN(dist) as decimal(10,2)) as shortest FROM 
  (SELECT SQRT((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)) AS dist FROM
    (SELECT t1.x as x1, t1.y as y1, t2.x as x2, t2.y as y2 from point_2d as t1, point_2d as t2) AS Tx) AS Ty
    WHERE dist > 0;
