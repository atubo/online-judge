SELECT CASE
  WHEN rid IS NULL THEN aid
  ELSE rid
  END AS id, COALESCE(outd, 0) + COALESCE(ind, 0) as num
  FROM
  
(SELECT * FROM 
  (SELECT requester_id AS rid, COUNT(requester_id) AS outd
    FROM request_accepted GROUP BY requester_id) AS t_out
  LEFT OUTER JOIN
  (SELECT accepter_id AS aid, COUNT(accepter_id) AS ind
     FROM request_accepted GROUP BY accepter_id) AS t_in
  ON t_out.rid=t_in.aid
  
  UNION
SELECT * FROM   
  (SELECT requester_id AS rid, COUNT(requester_id) AS outd
    FROM request_accepted GROUP BY requester_id) AS t_out
  RIGHT OUTER JOIN
  (SELECT accepter_id AS aid, COUNT(accepter_id) AS ind
     FROM request_accepted GROUP BY accepter_id) AS t_in
  ON t_out.rid=t_in.aid) as t
  
ORDER BY num DESC LIMIT 1;
