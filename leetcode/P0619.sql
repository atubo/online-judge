SELECT MAX(num) as num from
  (SELECT num from number GROUP by num HAVING COUNT(num) = 1) AS t;
