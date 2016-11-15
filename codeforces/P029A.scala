object P029A extends App {
  val n = readInt
  var pos    = (for (i <- 0 to n-1) yield 0) toArray
  var target = (for (i <- 0 to n-1) yield 0) toArray
  var lookup = collection.mutable.Map[Int, Int]()
  for (i <- 0 to n-1) {
    var elems = readLine.split(' ').map(x => x.toInt)
    pos(i)    = elems(0)
    target(i) = elems(0) + elems(1)
    lookup += ((pos(i), i))
  }
  println(if ((0 to n-1).exists(x => lookup.contains(target(x)) && lookup.get(target(lookup(target(x)))).getOrElse(null) == x)) "YES" else "NO")
}
