SELECT t2.Id AS Id, t1.Company AS Company, t2.Salary AS Salary
FROM

(
SELECT Company, COUNT(*) AS total
FROM Employee
GROUP BY Company
) AS t1

JOIN

(
SELECT e2.Id AS Id, e2.Company AS Company, e2.Salary AS Salary, COUNT(e1.Id) AS rank
FROM Employee e1, Employee e2
WHERE e1.Company=e2.Company AND (e1.Salary<e2.Salary OR (e1.Salary=e2.Salary AND e1.Id<=e2.Id))
GROUP BY e2.Id
ORDER BY e2.Salary
) AS t2
ON t1.Company=t2.Company

WHERE t2.rank=floor((t1.total+1)/2) OR t2.rank=floor((t1.total+2)/2)
;
