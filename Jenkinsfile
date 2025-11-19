pipeline {
    agent any

    environment {
        SONARCLOUD_URL = "https://sonarcloud.io"
        ORG = "your-org"
        PROJECT = "Static-3"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                echo "Build step..."
            }
        }

        stage('Upload to SonarCloud') {
            steps {
                withCredentials([string(credentialsId: 'SONAR_CLOUD_TOKEN', variable: 'TOKEN')]) {
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

                    sleep 10

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
                    }
                }
            }
        }

        stage('Deploy') {
            steps {
                echo "Done"
            }
        }
    }
}
