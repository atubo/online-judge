SELECT america.name AS America, asia.name AS Asia, europe.name AS Europe
FROM

(
    SELECT student.*, @rank1:=@rank1+1 rank
    FROM (SELECT @rank1:=0) r, student
    WHERE continent="America"
    ORDER BY student.name
) america

LEFT OUTER JOIN

(
    SELECT student.*, @rank2:=@rank2+1 rank
    FROM (SELECT @rank2:=0) r, student
    WHERE continent="Asia"
    ORDER BY student.name
) asia

ON america.rank=asia.rank

LEFT OUTER JOIN
(
    SELECT student.*, @rank3:=@rank3+1 rank
    FROM (SELECT @rank3:=0) r, student
    WHERE continent="Europe"
    ORDER BY student.name
) europe

ON america.rank=europe.rank
;
