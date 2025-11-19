pipeline {
    agent any

    environment {
        SONARCLOUD_URL = "https://sonarcloud.io"
        ORG = "mightykarim"          // your SonarCloud org (matches GitHub login/org)
        PROJECT = "Static-3"         // your GitHub repo/project name
    }

    stages {

        stage('Checkout') {
            steps {
                // Checkout your GitHub repo
                git branch: 'main', url: 'https://github.com/mightykarim/Static-3.git'
            }
        }

        stage('Build') {
            steps {
                echo "Build step..."
                // Add real build commands here if needed, e.g., npm install, mvn package
            }
        }

        stage('Upload to SonarCloud') {
            steps {
                withCredentials([string(credentialsId: 'sonarcloud-token', variable: 'TOKEN')]) {
                    sh """
                        curl -X POST "$SONARCLOUD_URL/api/scanner/scan" \
                            -H "Authorization: Bearer $TOKEN" \
                            -F "projectKey=$PROJECT" \
                            -F "organization=$ORG" \
                            -F "code=@."
                    """
                }
            }
        }

        stage('Quality Gate Check') {
            steps {
                script {
                    echo "Checking Quality Gate..."

                    sleep 10 // Wait for SonarCloud analysis to complete

                    def status = sh(
                        script: """
                            curl -s -H "Authorization: Bearer $TOKEN" \
                                "$SONARCLOUD_URL/api/qualitygates/project_status?projectKey=$PROJECT"
                        """,
                        returnStdout: true
                    ).trim()

                    echo "Response: $status"

                    if (status.contains('"status":"ERROR"')) {
                        error("❌ Quality Gate Failed")
                    } else {
                        echo "✅ Quality Gate Passed"
                    }
                }
            }
        }

        stage('Deploy') {
            steps {
                echo "Done — Deployment stage (runs only if Quality Gate passes)"
            }
        }
    }
}
