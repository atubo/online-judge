SELECT salesperson.name as name FROM salesperson LEFT JOIN
(
  SELECT company.name as com_name, t1.sales_id as sales_id, t1.name as name FROM
    (SELECT name, salesperson.sales_id, com_id FROM salesperson JOIN orders ON salesperson.sales_id=orders.sales_id) as t1
     JOIN company ON t1.com_id=company.com_id WHERE company.name='RED'
  ) as t2 ON salesperson.sales_id=t2.sales_id WHERE com_name is null;
