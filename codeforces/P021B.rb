def num_solutions(a1, b1, c1, a2, b2, c2)
  if a2 == 0 and b2 == 0
    if c2 != 0
      return 0
    else
      if a1 == 0 and b1 == 0
        return (c1 == 0 ? -1 : 0)
      else
        return -1
      end
    end
  end
  det = a1*b2-a2*b1
  return 1 if det != 0
  det2 = a1*c2-a2*c1
  det3 = b1*c2-b2*c1
  return ((det2 == 0  and det3 == 0) ? -1 : 0)
end

a1, b1, c1 = gets.split.map(&:to_i)
a2, b2, c2 = gets.split.map(&:to_i)

if a1 == 0 and b1 == 0
  a1, b1, c1, a2, b2, c2 = a2, b2, c2, a1, b1, c1
end

puts num_solutions(a1, b1, c1, a2, b2, c2)
