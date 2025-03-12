run() {
        make

        ./calib run.mac

        echo "simulation completed!"

        root -l photoncounting.C
}
