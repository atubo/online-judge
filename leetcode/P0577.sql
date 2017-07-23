SELECT Employee.Name as name, Bonus.Bonus as bonus FROM Employee LEFT JOIN Bonus ON Employee.EmpId=Bonus.EmpId
  WHERE Bonus.Bonus is null or Bonus.Bonus<1000;
