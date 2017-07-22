SELECT mname as Name FROM
  (SELECT COUNT(t1.Id) as reports, t1.ManagerId as mid, t2.Name as mname
    FROM Employee as t1, Employee as t2
    WHERE t1.ManagerId=t2.Id GROUP BY mid) as t
  WHERE reports>=5;
