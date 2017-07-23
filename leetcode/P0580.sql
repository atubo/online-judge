SELECT dept_name, COUNT(student_id) as student_number from department LEFT JOIN student on student.dept_id=department.dept_id
 GROUP BY dept_name ORDER BY student_number DESC, dept_name;
