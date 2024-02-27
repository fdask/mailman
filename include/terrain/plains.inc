<?php
namespace Terrain;

class Plains extends \Terrain {   
    public function __toString() {
        if ($this->isVisible()) {
            return "P" . $this->getCost();
        } else {
            return "XX";
        }
    }
}