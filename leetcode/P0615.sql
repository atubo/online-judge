SElECT t1.pay_month AS pay_month, t1.did AS department_id, CASE
WHEN t1.department_avg>t2.company_avg THEN "higher"
WHEN t1.department_avg=t2.company_avg THEN "same"
ELSE "lower"
END AS comparison

FROM
(
SELECT department_id AS did, AVG(amount) AS department_avg, date_format(pay_date, "%Y-%m") AS pay_month
FROM salary JOIN employee ON salary.employee_id=employee.employee_id
GROUP BY department_id, pay_month
  ) t1
  
JOIN

(
SELECT AVG(amount) as company_avg, date_format(pay_date, "%Y-%m") as pay_month
FROM salary
GROUP BY pay_month
  ) t2
  
ON t1.pay_month=t2.pay_month
ORDER BY t1.pay_month DESC
;
