object P026B {
  def main(args: Array[String]) = {
    val s = readLine.map(x => -(x.toInt)*2 + 81)
    val n = s.size
    var l = n
    var sum = 0
    for (i <- 0 to n-1) {
      if (sum + s(i) >= 0) {
        sum += s(i)
      }
      else {
        l -= 1;
      }
    }
    println(l-sum)
  }
}

