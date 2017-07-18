SELECT t.id as id, CASE
  WHEN t.p_id is null THEN 'Root'
  WHEN as_p_id is null THEN 'Leaf'
  ELSE 'Inner'
  END AS Type
  FROM

(SELECT tree.id as id, tree.p_id as p_id, t_p.p_id as as_p_id FROM
  tree LEFT JOIN
  (SELECT DISTINCT p_id FROM tree WHERE p_id IS NOT null) as t_p
  ON tree.id=t_p.p_id) as t
  
  ORDER BY id;
