pipeline {
    agent any
    
    environment {
        SONAR_URL = 'http://localhost:9000'
    }
    
    stages {
        stage('Checkout') {
            steps {
                sh 'git clone https://github.com/mightykarim/Static-3.git . || true'
            }
        }
        
        stage('Test Scan') {
            steps {
                sh '''
                    echo "Testing SonarQube connection..."
                    
                    # Create minimal config
                    cat > sonar-project.properties << 'EOF'
sonar.projectKey=Static-3-Test
sonar.projectName=Static-3-Test
sonar.sources=.
sonar.sourceEncoding=UTF-8
EOF
                    
                    # Try scan (may fail without auth, but shows scanner works)
                    /opt/sonar-scanner-5.0.1.3006/bin/sonar-scanner \
                        -Dsonar.projectKey=Static-3-Test \
                        -Dsonar.host.url=http://localhost:9000 \
                        -Dsonar.sources=. || echo "Scan attempted (auth may be needed)"
                    
                    echo "Test complete!"
                '''
            }
        }
    }
}
