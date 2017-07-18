SELECT t1.fname AS follower, COUNT(t1.fname) AS num FROM

  (SELECT DISTINCT(follower) AS fname FROM follow) AS t1
  JOIN (SELECT DISTINCT followee, follower FROM follow) AS t2 ON t1.fname=t2.followee
  GROUP BY t1.fname ORDER BY t1.fname;  
