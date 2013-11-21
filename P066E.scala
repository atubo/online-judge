object P066E extends App {
  def ps(a:List[Int])={
    a.scan(0)(_+_).drop(1)
  }
  def calc(a:List[Int], b:List[Int], n:Int):Set[Int] = {
    val c = (ps(a) zip ps(b)).map(x=>x._1-x._2)
    val x = c.min
    val d = c.zipWithIndex.filter(_._1==x).map(x=>(x._2+1)%n)
    return d.toSet
  }

  val n = readInt
  val a = readLine.split(' ').map(_.toInt).toList
  val b = readLine.split(' ').map(_.toInt).toList
  val s1 = calc(a, b, n)
  val s2 = calc(a.reverse, (b.takeRight(1):::b.take(n-1)).reverse, n).map(x=>n-1-x)
  val s = s1.union(s2).map(x=>x+1)
  println(s.size)
  println(s.toArray.sorted.deep.mkString(" "))
}
