<?php
class Path {
    // an array holding the terrain objects
    public $terrain;

    // string name of the originating town
    public $origTown;

    // string name of the destination town
    public $destTown;

    // where is the player on the path
    public $yPos;

    public function __construct($orig = false, $dest = false) {
        $this->terrain = array();

        // add random terrain
        for ($x = 0; $x < 5; $x++) {
            $this->terrain[] = new Terrain\Plains();
        }

        $this->yPos = 0;

        if ($orig) {
            $this->origTown = $orig;
        }

        if ($dest) {
            $this->destTown = $orig;
        }
    }

    public function getDistance() {
        return count($this->terrain);
    }

    public function setDestTown($d) {
        $this->destTown = $d;
    }

    public function getDestTown() {
        return $this->destTown;
    }

    public function getOrigTown() {
        return $this->origTown;
    }

    public function getTerrain($y) {
        // return the terrain at position $y
        if (isset($this->terrain[$y])) {
            return $this->terrain[$y];
        }

        return false;
    }

    private function terrainToString() {
        // origin town
        if ($this->yPos == 0) {
            $ret = Colors::bg_color("light_gray", "T");
        } else {
            $ret = "T";
        }
        
        $ret .= "-";

        foreach ($this->terrain as $count => $t) {
            if ($count == $this->yPos - 1) {
                $ret .= "[" . Colors::bg_color("light_gray", $t) . "]-";
            } else {
                $ret .= "[$t]-";
            }
        }

        // destination town
        if (count($this->terrain) + 1 == $this->yPos) {
            $ret .= Colors::bg_color("light_gray", "T");
        } else {
            $ret .= "T";
        }

        return $ret;
    }

    public function reversePath() {
        $this->terrain = array_reverse($this->terrain);
        
        $tmp = $this->origTown;
        $this->origTown = $this->destTown;
        $this->destTown = $tmp;
    }

    public function moveLeft() {
        if ($this->yPos > 0) {
            $this->yPos--;

            if (isset($this->terrain[$this->yPos - 1])) {
                $this->terrain[$this->yPos - 1]->setVisible();
            }
        }
    }

    public function moveRight() {
        if ($this->yPos <= $this->getDistance()) {
            $this->yPos++;
            
            if (isset($this->terrain[$this->yPos - 1])) {
                $this->terrain[$this->yPos - 1]->setVisible();
            }
        }
    }

    public function __toString() {
        $ret = "PATH: ";

        $ret .= $this->terrainToString() . " ";
        $ret .= "yPos: " . $this->yPos . "\n";
        
        return $ret;
    }
}