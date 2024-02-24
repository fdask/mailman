<?php
class Config {
    public static $debug = true;
    
    public static function autoload($class) {
        $file = __DIR__ . "/include/" . str_replace('\\', '/', strtolower($class)) . ".inc";
        
        if (file_exists($file)) {
            require $file;
        } else {
            if (Config::$debug) {
                debug_print_backtrace();
            }
            
            die("Couldnt find file: $file\n");
        }
    }
}

spl_autoload_register("Config::autoload");
