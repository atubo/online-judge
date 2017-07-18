SELECT CASE
WHEN req=0 THEN 0.00
ELSE CAST(acc/req AS DECIMAL(10,2))
END AS accept_rate
FROM
  (SELECT 1 AS id, COUNT(*) AS acc FROM
    (SELECT DISTINCT requester_id, accepter_id FROM request_accepted) AS t1) AS t3
  
  JOIN

  (SELECT 1 AS id, COUNT(*) AS req FROM
    (SELECT DISTINCT sender_id, send_to_id FROM friend_request) AS t2) AS t4;
