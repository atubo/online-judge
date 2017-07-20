SELECT CAST(AVG(Number) AS DECIMAL(10, 4)) AS median 
FROM
(
(SELECT t1.Number as Number, t1.accu as accu, t2.total as total
FROM

(
SELECT n2.Number AS Number, SUM(n1.Frequency) AS accu
FROM Numbers n1, Numbers n2
WHERE n1.Number<=n2.Number
GROUP BY n2.Number
ORDER BY Number
) AS t1
,
(
SELECT SUM(Frequency) AS total
FROM Numbers
) AS t2

WHERE accu>=floor((total+1)/2) LIMIT 1)
UNION

(SELECT t1.Number as Number, t1.accu as accu, t2.total as total
FROM

(
SELECT n2.Number AS Number, SUM(n1.Frequency) AS accu
FROM Numbers n1, Numbers n2
WHERE n1.Number<=n2.Number
GROUP BY n2.Number
ORDER BY Number
) AS t1
,
(
SELECT SUM(Frequency) AS total
FROM Numbers
) AS t2

WHERE accu>=floor((total+2)/2) LIMIT 1)
) as t3
;
