SELECT * FROM
(SELECT Candidate.Name as Name FROM Vote LEFT JOIN Candidate ON Vote.CandidateId=Candidate.id
        GROUP BY Vote.CandidateId ORDER BY COUNT(Vote.CandidateId) DESC LIMIT 1) as t
    WHERE name is not null;
