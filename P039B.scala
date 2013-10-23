object P039B extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  var curr = 0
  var resultBuilder = new collection.mutable.ArrayBuilder.ofInt()
  for (i <- 0 to n-1) {
    if (a(i) == curr + 1) {
      resultBuilder += 2001 + i
      curr += 1
    }
  }
  if (curr == 0) {
    println(0)
  }
  else {
    val result = resultBuilder.result()
    println(result size)
    println(result.deep.mkString(" "))
  }
}

