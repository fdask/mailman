<?php
class Map {
    private $paths;
    private $towns;

    public function __construct() {
        $this->paths = array();
        $this->towns = array();
    }

    public function addPath(Path $p) {
        // don't clobber an existing path
        $replaced = false;

        for ($x = 0; $x < count($this->paths); $x++) {
            if ($this->paths[$x]->getOrigTown() == $p->origTown && $this->paths[$x]->getDestTown() == $p->destTown) {
                // replace an existing path
                $replaced = true;
                $this->paths[$x] = $p;
            }
        }

        if (!$replaced) {
            $this->paths[] = $p;
        }
    }

    // do we have a path?
    public function havePath($origTown, $destTown) {
        foreach ($this->paths as $p) {
            if ($p->getOrigTown() == $origTown && $p->getDestTown() == $destTown) {
                return true;
            }
        }

        return false;
    }

    public function getPath($origTown, $destTown) {
        foreach ($this->paths as $p) {
            if ($p->getOrigTown() == $origTown && $p->getDestTown() == $destTown) {
                return $p;
            }
        }

        return false;
    }
 
    public function addTown(Town $t) {
        $this->towns[$t->getName()] = $t;
    }

    public function getTown($town) {
        if (isset($this->towns[$town])) {
            return $this->towns[$town];
        }

        return false;
    }

    public function getTowns($exclude = null) {
        $ret = array();

        if (count($this->towns)) {
            foreach ($this->towns as $name => $town) {
                if ($exclude && $name == $exclude) {
                    continue;
                }

                $ret[] = $name;
            }
        }

        return $ret;
    }

    public function __toString() {
        $ret = "Towns: " . implode(",", array_keys($this->towns)) . "\n";

        return $ret;
    }
}