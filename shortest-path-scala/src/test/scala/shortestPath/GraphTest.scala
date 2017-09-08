package shortestPath

object GraphTest extends shortestPath{
    def main(args: Array[String]): Unit = {
        val A = new Node("A")
        val B = new Node("B")
        val C = new Node("C")
        val D = new Node("D")
        val E = new Node("E")

        val g: Graph = Map("A" -> A, "B" -> B, "C" -> C, "D" -> D, "E" -> E)

        g("A").neighbors = ("B", 7) :: ("C", 1) :: Nil
        g("B").neighbors = ("A", 7) :: ("D", 2) :: Nil
        g("C").neighbors = ("A", 1) :: ("D", 3) :: Nil
        g("D").neighbors = ("B", 2) :: ("C", 3) :: ("E", 2) :: Nil
        g("E").neighbors = ("D", 2) :: Nil

        //        dijkstra(g, "A")
        spfa(g, "A")
        printGraph(g)
    }
}
