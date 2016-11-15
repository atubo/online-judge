object P025B {
  def main(argv: Array[String]) = {
    val n = readInt
    var s = readLine
    val firstWidth = n % 2 + 2
    print(s.slice(0, firstWidth))
    s = s.drop(firstWidth)
    while (s.length() > 0) {
      print('-' + s.slice(0, 2))
      s = s.drop(2)
    }
    println()
  }
}

